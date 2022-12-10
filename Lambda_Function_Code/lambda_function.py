import json
import boto3
import botocore
import datetime as dt
import requests
from bs4 import BeautifulSoup


def kelvin_to_celsius_and_fahrenheit(kelvin):
    """convert a kelvin temp into celcius and fahrenheit temperatrues

    Args:
        kelvin (float): the temperature in kelvin to convert

    Returns:
        tuple: the temp convertedt to celsius, and farenheit
    """
    celsius = kelvin - 273.15

    fahrenheit = (celsius * 9 / 5) + 32

    return celsius, fahrenheit

# function to get the weather


def getWeather():
    """Get Local Weather Data for watering descion

    Returns:
        tuple: the current city, percent chance of rain, current temp, percent humidity, sky description, and sunrise, and sunset times
    """
    weather_url = 'https://weather.com/weather/today/l/34ca4f55af04e43b8206804a5247bfdbe7402506bae151bd84b87d3c55e1dddd'
    page = requests.get(weather_url)
    soup = BeautifulSoup(page.content, "html.parser")

    location = soup.find('h1', class_='CurrentConditions--location--1YWj_').text
    temperature = soup.find('span', class_='CurrentConditions--tempValue--MHmYY').text
    chance_of_rain = soup.find_all('span', class_='Column--precip--3JCDO')[2].text[-2:]
    
    # openweathermap API
    base_url = "https://api.openweathermap.org/data/2.5/weather?"
    API_key = "1259032a7ce138f20a8dd92db5b2594f"

    # sending request to openweathermap API
    current_city = "Fort Myers"
    open_url = base_url + "appid=" + API_key + "&q=" + current_city
    response = requests.get(open_url).json()

    # weather data from openweathermap API
    temp_kelvin = response['main']['temp']
    temp_celsius, temp_fahrenheit = kelvin_to_celsius_and_fahrenheit(temp_kelvin)
    humidity = response['main']['humidity']
    sky_description = response['weather'][0]['description']
    sunrise_time = dt.datetime.utcfromtimestamp(response['sys']['sunrise'] + response['timezone'])
    sunset_time = dt.datetime.utcfromtimestamp(response['sys']['sunset'] + response['timezone'])


    return current_city, chance_of_rain, temp_fahrenheit, humidity, sky_description, sunrise_time, sunset_time

def send_email(body_text):
    """ Send a SES email with the weather data that was collected

    Args:
        body_text: HTML that's makes up the body of the email

    Returns:
        None
    """
    SENDER = "jjburnham1@gmail.com"
    RECIPIENT = "jjburnham0705@eagle.fgcu.edu"
    AWS_REGION = "us-east-1"
    SUBJECT = "Auto-Plant-Ic Daily Water Report"
    BODY_TEXT = ()

    BODY_HTML = f"""<html>
                    <head></head>
                    <body>
                      <h1>Auto-Plant-Ic Daily Report</h1>
                      <p> {body_text}</p>
                    </body>
                   </html>
            """ 
    CHARSET = "UTF-8"
    
    client = boto3.client('ses',region_name=AWS_REGION)
    
    try:
        #Provide the contents of the email.
        response = client.send_email(
            Destination={
                'ToAddresses': [
                    RECIPIENT,
                ],
            },
            Message={
                'Body': {
                    'Html': {
                        'Charset': CHARSET,
                        'Data': BODY_HTML,
                    },
                    'Text': {
                        'Charset': CHARSET,
                        'Data': str(BODY_TEXT),
                    },
                },
                'Subject': {
                    'Charset': CHARSET,
                    'Data': SUBJECT,
                },
            },
            Source=SENDER
        )
    # Display an error if something goes wrong.	
    except botocore.exceptions.ClientError as e:
        raise(e)
    else:
        print("Email sent! Message ID:"),
        print(response['MessageId'])


def lambda_handler(event, context):
    """The handler for the lambda function this is required by the lambda function

    Args:
        event (dict): json dump of the event that triggered the lambda
        context (dict): json dump of the context passed to the lambda 

    Returns:
        json: the API response on wether to water the plant or not
    """
    
    try: # try to get humidity
        humidity = event['multiValueQueryStringParameters']['humidity']
    except KeyError:
        humidity = 0
        
    try: # try to get soil moisture
        soil_moisture = event['multiValueQueryStringParameters']['soil_moisture']
    except KeyError:
        soil_moisture = 0
        
    try: # try to get temperature
        temperature = event['multiValueQueryStringParameters']['temperature']
    except KeyError:
        temperature = 0 
        
        
    # get weather data
    current_city, chance_of_rain, temp_fahrenheit, humidity, sky_description, sunrise_time, sunset_time = getWeather()
    
    # make descion
    descision = ''
    num_chance_rain = int(chance_of_rain[0])
    if (num_chance_rain >= 65):
        
        descision = 'water'
        
    else:
        descision = 'nothing'
    
    
    # make the body of the email with descion made
    body_text = f"This is your daily weather report for {current_city}. <br>"
    body_text += f"Time of Sunrise: {sunrise_time}, Time of Sunset: {sunset_time} <br>"
    body_text += f"Current Temperature: {temp_fahrenheit}, Current Humidity: {humidity} <br>"
    body_text += f"Also, the sky over {current_city} is going to be {sky_description}, with a {chance_of_rain} of rain <br>"
    body_text += f"<br> Based on your local weather Auto-Plant-Ic decided to do {descision}"
    
    send_email(str(body_text))
    
    # send the API response
    return {
        'statusCode': 200,
        'body': json.dumps(descision)
    }
