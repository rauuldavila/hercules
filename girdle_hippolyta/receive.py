# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    receive.py                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rdavila <rdavila@student.42.us.org>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/14 17:38:21 by rdavila           #+#    #+#              #
#    Updated: 2017/04/14 20:48:53 by rdavila          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import imaplib
import email
import os
import sys

def error(message):
	print 'Error: ', message
	sys.exit(1)

# Connect to server
try:
	mail = imaplib.IMAP4_SSL('imap.gmail.com')
	mail.login('rdvmtz@gmail.com', os.environ['GMAIL_TOKEN'])
	mail.list()
	mail.select("inbox")
except:
	error('IMAP connection failed. Check your credentials and try again.')

# Get latest mail
try:
	result, data = mail.search(None, "ALL")
	mail_ids = data[0].split()
	latest = mail_ids[-1]
	# Fetch the email body (RFC822) for the given ID
	result, data = mail.fetch(latest, "(RFC822)")
except:
	error('Failed to fetch mail list.')

# Get the raw email data
raw_email = data[0][1]

email = email.message_from_string(raw_email)
print 'Date received:\t', email['Date']
print 'Sender:\t\t', email['From']

# Body details
for part in email.walk():
	if part.get_content_type() == "text/plain":
		body = part.get_payload(decode=True)
		print '----------\n', body, '\n----------'
	else:
		continue
