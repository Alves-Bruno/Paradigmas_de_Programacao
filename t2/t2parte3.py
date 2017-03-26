#!/usr/bin/env python3
import sys
from lxml import html, etree
import requests


def decifra(string):
	return ''.join([chr(int(x, 16)) for x in string.split()])

def main():

	url = 'http://desafio-paradigmas.appspot.com'
	page = requests.get(url)
	tree = html.fromstring(page.content)
	content = tree.xpath("//comment()")
	hexText = str(content[0].xpath('string()'))

	decifrado = decifra(hexText[hexText.find(':') + 1:])
	print(decifrado)

if __name__ == '__main__':
	main()
