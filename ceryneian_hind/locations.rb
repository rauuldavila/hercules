# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    locations.rb                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rdavila <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/24 16:09:45 by rdavila           #+#    #+#              #
#    Updated: 2017/02/24 16:09:50 by rdavila          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

require "oauth2"

UID = "66633ff524a85b06035d6b3d573fd05cb0947f2b190d51451f0175ca8d3d7401"
SECRET = ENV["API_SECRET"]

if ARGV.length == 0
	abort "\nError: missing file name.\n\n"
elsif ARGV.length > 1
	abort "\nError: too many arguments\n\n"
end

client = OAuth2::Client.new(UID, SECRET, site: "https://api.intra.42.fr")
token = client.client_credentials.get_token

File.open(ARGV[0], "r") do |f|
	f.each_line do |line|
		uid = line.chomp
		begin
			ret = token.get("/v2/users/#{uid}/locations?filter[active]=true").parsed
			if ret[0]
				host = ret[0]["host"]
				puts "User #{uid} is in #{host}."
			else
				puts "User #{uid} is taking a nap."
			end
		rescue
			puts "User #{uid} isn't registered."
		end
	end
end
