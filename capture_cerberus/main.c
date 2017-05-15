/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdavila <rdavila@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 19:33:38 by rdavila           #+#    #+#             */
/*   Updated: 2017/05/07 19:34:59 by rdavila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_socket.h"

void	error(char *msg)
{
	printf(RED"%s\n", msg);
	exit(1);
}

int		main(int argc, char **av)
{
	struct sockaddr_in	serv_addr;
	int					sockfd;

	if (argc < 2)
		error("usage: ./proxy [PORT_NUMBER]");
	printf(RED"----------WELCOME TO 42 PROXY SERVER----------\n\n"RESET);
	bzero((char*)&serv_addr, sizeof(serv_addr));
	sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sockfd < 0)
		error("Error initializing socket");
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(atoi(av[1]));
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	if (bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
		error("Error on binding");
	listen(sockfd, 50);
	while (1)
		ft_socket(sockfd);
	return (0);
}
