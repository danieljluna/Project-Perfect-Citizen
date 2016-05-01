import requests
import json
r = requests.get('http://ipinfo.io')

print r.text

f = open('workfile', 'w')
f.write(r.text)