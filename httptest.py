import email, smtplib, ssl
from email import encoders
from email.mime.base import MIMEBase
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart
import sys


class MyMail:

    def __init__(self):
        self.sender_email = "bkotwall6928@eagle.fgcu.edu"
        self.receiver_email = "bkotwall6928@eagle.fgcu.edu"
        self.sender_password = None
        self.email_subject = "python_email"
        self.email_body = "Testingtesting"
        self.path_to_attachment = None

    def get_sender_details(self):
        print("Enter the email of the sender::")
        self.sender_email = input()
        print("Enter the Password of the sender::")
        self.sender_password = input()

    def get_reciever_details(self):
        print("Enter the email of the receiver::")
        self.receiver_email = input()

    def get_email_details(self):
        print("Enter the Subject of the sending email::")
        self.email_subject = input()
        print("Enter the Body of the sending email::")
        self.email_body = input()

    def get_attachment(self):
        print("Enter the path of the attachment for the sending email::")
        self.path_to_attachment = input()

    def print_details(self):
        print("Sender Mail::")
        print(self.sender_email)
        print("Receiver Mail::")
        print(self.receiver_email)
        print("Email Subject::")
        print(self.email_subject)
        print("Email Body::")
        print(self.email_body)

    def send_email(self, objj1=None):
        message = MIMEMultipart("alternative")
        message["Subject"] = self.email_subject
        message["From"] = self.sender_email
        message["To"] = self.receiver_email

        text = """\\{}""".format(self.email_body)
        html = """\  
        <html>  
          <body>  
            <p>Hi,<br>  
               test email<br> .  
            </p>  
          </body>  
        </html>  
        """

        obbj1 = MIMEText(text, "html")
        objj2 = MIMEText(html, "plain")

        message.attach(objj1)
        message.attach(objj2)

        with open(self.path_to_attachment, "br") as attachment:
            part = MIMEBase("application", "octet-stream")
            part.set_payload(attachment.read())

        encoders.encode_base64(part)


        part.add_header(
            "Content-Disposition",
            "attachment; filename= {self.path_to_attachment}",
        )

        message.attach(part)

        context111 = ssl.create_default_context()
        with smtplib.SMTP_SSL("smtp.gmail.com", 465, context=context111) as server:
            server.login(self.sender_email, self.sender_password)
            server.sendmail(self.sender_email, self.receiver_email, message.as_string())

        print("Email sent successfully.")

def main():
    mailer = MyMail()

    while (True):
        print("Please choose one of the below-listed options::")
        print("1. To enter the details of the sender. [Sender email and sender Password]")
        print("2. To enter the details of the receiver. [Receiver email]")
        print("3. To enter the Subject and Body of the sending email.")
        print("4. To enter the attachment for the sending email.")
        print("5. To send the email.")
        print(
            "6. To verify all the entered details. [Sender email, Sender Password, Receiver email, Email Subject and Email Body.")
        print("7. To exit from the code execution.")
        menu_choice = input()
        menu_choice = int(menu_choice)

        if menu_choice == 1:
            mailer.get_sender_details()

        elif menu_choice == 2:
            mailer.get_reciever_details()

        elif menu_choice == 3:
            mailer.get_email_details()

        elif menu_choice == 4:
            mailer.get_attachment()

        elif menu_choice == 5:
            print("Email sent successfully.")

        elif menu_choice == 6:
            mailer.print_details()

        elif menu_choice == 7:
            sys.exit()

        print("wanna proceed with the program or want to exit the program [Y/n]")
        continue_or_exit = input()

        if continue_or_exit == 'y' or continue_or_exit == 'Y':
            pass
        elif continue_or_exit == 'n' or continue_or_exit == 'N':
            sys.exit()


if __name__ == '__main__':
    main()  