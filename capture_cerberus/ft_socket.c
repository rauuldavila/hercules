/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_socket.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdavila <rdavila@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 19:33:57 by rdavila           #+#    #+#             */
/*   Updated: 2017/05/07 19:38:51 by rdavila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_socket.h"

char	*parse_url(char *url, char *format)
{
	char	*url_copy;
	char	*domain;
	char	*path;

	url_copy = strdup(url);
	if (!strcmp(format, "domain"))
	{
		domain = strtok(url_copy, "//");
		domain = strdup(strtok(NULL, "/"));
		return (domain);
	}
	if (!strcmp(format, "path"))
	{
		url_copy += 8;
		path = strchr(url_copy, '/');
		return (path);
	}
	return (NULL);
}

int		ft_host_connection(char *domain)
{
	struct sockaddr_in	host_addr;
	struct hostent		*host;
	int					sockfd;
	int					n;

	host = gethostbyname(domain);
	bzero((char*)&host_addr, sizeof(host_addr));
	host_addr.sin_port = htons(80);
	host_addr.sin_family = AF_INET;
	bcopy((char*)host->h_addr, (char*)&host_addr.sin_addr.s_addr,
			host->h_length);
	sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	n = connect(sockfd, (struct sockaddr*)&host_addr, sizeof(struct sockaddr));
	if (n < 0)
		error("Error in connecting to remote server");
	printf(GRN"Connected to %s [ %s ]\n\n"RESET,
			domain, inet_ntoa(host_addr.sin_addr));
	return (sockfd);
}

void	ft_process_request(int sockfd_client, char *url, char *protocol)
{
	int		sockfd_host;
	int		n;
	char	buffer[500];
	char	*path;
	char	*domain;

	domain = parse_url(url, "domain");
	path = parse_url(url, "path");
	printf(CYN"Host: %s\nPath: %s\nPort: 80\n"RESET, domain, path);
	sockfd_host = ft_host_connection(domain);
	bzero((char*)buffer, sizeof(buffer));
	sprintf(buffer, "GET %s %s\r\nHost: %s\r\nConnection: close\r\n\r\n",
			path, protocol, domain);
	n = send(sockfd_host, buffer, strlen(buffer), 0);
	if (n < 0)
		error("Error writing to socket");
	n = 1;
	while (n > 0)
	{
		bzero((char*)buffer, 500);
		n = recv(sockfd_host, buffer, 500, 0);
		if (n > 0)
			send(sockfd_client, buffer, n, 0);
	}
	close(sockfd_host);
}

void	ft_validate_request(char *buffer, int sockfd_client)
{
	char				request[300];
	char				protocol[10];
	char				url[300];

	sscanf(buffer, "%s %s %s", request, url, protocol);
	if ((!strncmp(request, "GET", 3)) &&
		(!strncmp(protocol, "HTTP/1.1", 8)
		|| !strncmp(protocol, "HTTP/1.0", 8)) &&
		(!strncmp(url, "http://", 7)))
	{
		ft_process_request(sockfd_client, url, protocol);
	}
	else
		send(sockfd_client,
				"400 : BAD REQUEST\nONLY HTTP REQUESTS ALLOWED", 18, 0);
}

void	ft_socket(int sockfd)
{
	struct sockaddr_in	cli_addr;
	int					sockfd_client;
	socklen_t			clilen;
	char				buffer[500];

	clilen = sizeof(cli_addr);
	sockfd_client = accept(sockfd, (struct sockaddr*)&cli_addr, &clilen);
	if (sockfd_client < 0)
		error("Problem in accepting connection");
	bzero((char*)buffer, 500);
	recv(sockfd_client, buffer, 500, 0);
	ft_validate_request(buffer, sockfd_client);
}
