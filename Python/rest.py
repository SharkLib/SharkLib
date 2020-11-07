import requests

url = "192.168.1.101:8000/api/users"

payload={}
headers = {
  'Authorization': 'Basic cm9uZzpHb29kMjAxNyE=',
  'Cookie': 'csrftoken=remjP1K2afoWUj679ZQdtZg3F2tU0paa1MwbSEgLThS0f2e4oot5MDKfeBWk8OfY'
}

response = requests.request("GET", url, headers=headers, data=payload)

print(response.text)




r = requests.get('http://127.0.0.1:8000/api/users', auth=('rong', 'Good2017!'))
print(r.text)