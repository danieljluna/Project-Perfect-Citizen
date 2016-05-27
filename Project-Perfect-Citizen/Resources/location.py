import requests
import json
r = requests.get('http://ipinfo.io')

print r.text

f = open('loc_file.txt', 'w')
f.write(r.text)