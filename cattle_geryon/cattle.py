# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    cattle.py                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rdavila <rdavila@student.42.us.org>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/22 18:03:16 by rdavila           #+#    #+#              #
#    Updated: 2017/04/22 18:03:19 by rdavila          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import requests
import sys
import time

# Set up parameters
url = 'http://getbootstrap.com'
max_hits = 5
clients = 5
data = {
	'transactions': clients * max_hits,
	'success': 0,
	'failure': 0,
	'time': 0,
	'size': 0
}

# Check for valid url
try:
	r = requests.get(url)
	print 'STARTING SERVER BENCHMARKING'
	print 'URL:\t\t', url
	print 'Clients:\t', clients
	print 'Requests:\t', max_hits, '\n'
	time.sleep(1.5)
except:
	print 'Bad url, stopping'
	sys.exit(1)

# Start benchmark
i = 0
while i < clients:
	hits = 0
	while hits < max_hits:
		r = requests.get(url)

		# Status of request
		status = r.status_code
		if status == 200:
			data['success'] += 1	
		else:
			data['failure'] += 1

		# Time of request
		time = str(r.elapsed)[5:-4]
		data['time'] += float(time)

		# Size of data transfered
		size = len(r.content)
		data['size'] += size

		# Method
		method = str(r.request)[18:-2]

		# Print request data
		print 'HTTP/1.1 ', status, '\t', time, 'secs\t', size, 'bytes ==>', method, '', url
		hits += 1

	i += 1

print '\nTransactions:\t\t\t', data['transactions'], 'hits'
print 'Availability:\t\t\t', (data['success'] * 100) / data['transactions'], '%'
print 'Elapsed time:\t\t\t', data['time'], 'secs'
print 'Average response time:\t\t', data['time'] / data['transactions'], 'secs'
print 'Data transfered:\t\t', data['size'] / 1024, 'KB'
print 'Successful transactions:\t', data['success']
print 'Failed transactions:\t\t', data['failure']
