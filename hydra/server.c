/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdavila <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 10:52:54 by rdavila           #+#    #+#             */
/*   Updated: 2017/02/17 21:52:00 by rdavila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int		main(int ac, char **av)
{
	int		sockfd;
	int		connfd;
	int		word_count;
	char	buffer[256];
	socklen_t addr_size;
	struct sockaddr_in server;

	if (ac != 2)
	{
		printf("usage: ./server [PORT]\n");
		return (0);
	}

	// Socket descriptor
	sockfd = socket(PF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
	{
		printf("error in socket\n");
		return (0);
	}

	// Clean structure
	memset(&server, '0', sizeof(server));

	// Set parameters for connection (protocol IPv4, any machine IP, port)
	server.sin_family = PF_INET;
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	server.sin_port = htons(atoi(av[1])); 

	// Connect the socket with struct parameters (IP, port..)
	if (bind(sockfd, (struct sockaddr*)&server, sizeof(server)) < 0)
	{
		printf("error in bind\n");
		return (0);
	}

	// Listen with max of 5 connections
	listen(sockfd, 5);

	while (1)
	{
		// Connect to client
		addr_size = sizeof(server);
		connfd = accept(sockfd, (struct sockaddr*)&server, &addr_size);
		if (connfd < 0)
		{
			write(1, "connection error\n", 17);
			return (0);
		}
		else
		{
			word_count = read(connfd, buffer, 255);
			buffer[word_count] = '\0'; 
			if (!strncmp(buffer, "ping", 4))
				write(connfd, "PONG\nPONG\n", 10);
		}
		// Close the connections
		close(connfd);
	}
	return (0);
}
