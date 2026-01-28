#!/bin/bash

PS3="Please select your desired city: "

select city in  Tokyo London "Los Angeles" Moscow Dubai Manchester "New York" Paris Bangalore Johannesburg Istanbul Milan "Abu Dhabi" Pune Nairobi Berlin Karachi
do
country=""
case "$city" in
	"Tokyo") country="Japan";;
	"London"|"Manchester") country="England";;
	"Los Angeles" | "New York") country="USA";;
	"Moscow" ) country="Russia";;
	"Dubai" | "Abu Dhabi" ) country="United Arab Emirates";;
	"Paris") country="France";;
	"Bangalore" | "Pune") country="India";;
	"Johannesburg") country="South Africa";;
	"Istanbul") country="Turkey";;
	"Milan") country="Italy";;
	"Nairobi") country="Kenya";;
	"Berlin") country="Germany";;
	"Karachi") country="Pakistan";;
	*) country= "Unlisted city";;
esac
echo The country where $city belongs is $country
break
done

