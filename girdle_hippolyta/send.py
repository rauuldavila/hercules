# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    send.py                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rdavila <rdavila@student.42.us.org>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/14 11:48:13 by rdavila           #+#    #+#              #
#    Updated: 2017/04/14 20:58:55 by rdavila          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import smtplib
import os
import sys
import time
from email.MIMEMultipart import MIMEMultipart
from email.MIMEText import MIMEText
from email.MIMEBase import MIMEBase
from email import encoders

sender = "rdvmtz@gmail.com"
recipient = "rauldavilams@gmail.com"

print 'Setting up basic parameters'
time.sleep(1)

# Set up MIME parameters
mail = MIMEMultipart()
mail['From'] = sender
mail['To'] = recipient
mail['Subject'] = "Girdle of Hippolyta"

# Attach the message
message = "<div style='text-align: center; height: 300px; background: -webkit-linear-gradient(left, #EE3C6C, #F7993D); padding-top: 150px;'><h2 style='color: #FFF'>HELP HERCULES</h2><p style='color: #fff; padding: 0 30px 18px 30px;'>Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum</p><button style='background: transparent; border: 3px solid #FFF; padding: 5px 15px 5px 15px;'><a href='http://www.theuselessweb.com/' style='color: #FFF; text-decoration: none;'>Help</a></button></div>"
mail.attach(MIMEText(message, 'html'))

# Attachments
attachments = ['pictures/ifox.jpg', 'pictures/panda.jpg']

# Add the attachments to the mail
for file in attachments:
	try:
		with open(file, 'rb') as fp:
			att = MIMEBase('application', "octet-stream")
			att.set_payload(fp.read())
		encoders.encode_base64(att)
		att.add_header('Content-Disposition', 'attachment; filename=%s' % os.path.basename(file))
		mail.attach(att)
		print 'Attaching', os.path.basename(file)
		time.sleep(1)
	except:
		print 'Unable to open', os.path.basename(file)

print 'Making SMTP connection'
time.sleep(1)

# Make connection and send the mail
try:
	# Gmail SMTP 
	server = smtplib.SMTP('smtp.gmail.com', 587)
	# Identify ourselves to SMTP gmail client
	server.ehlo()
	# Secure our email with TLS encryption
	server.starttls()
	# Re-identify ourselves as an encrypted connection
	server.ehlo()

	server.login(sender, os.environ['GMAIL_TOKEN'])
	server.sendmail(sender, recipient, mail.as_string())
	server.quit()
	print 'Email sent successfully' 
except:
	print 'Unable to send mail'
