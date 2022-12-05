import os
from dotenv import load_dotenv
import requests
from bs4 import BeautifulSoup

# cookie = "53616c7465645f5fc4d9045b0ebebd44af2443b422cb7c99413b881de401af17e6b05a50449be6bbc5dc2198aa0fc0ffdb49aed5984ff1a7ab73097327a4019a"
load_dotenv()
def main():
    cookie = os.environ["COOKIE"]

    HEADERS = {
        "cookie": f"session={cookie}"
    }

    result = requests.get("https://adventofcode.com", headers=HEADERS)

    print(f"Connection: {result.status_code}")
    if (result.status_code != 200):
        print(f"Something went wrong: {result.status_code}")

    content = result.content

    html = BeautifulSoup(content, "html.parser")

    print(html.find("span", {"id":"calendar-countdown"}).parent.findChild("span", class_="calendar-day").text)
    day = ""
    input_url = ""
    while day == "":
        day = input("Day: ")
        element = html.select(f"[h']")[0]
        if (element.findChild("span", {"id": "calendar-countdown"}) != None):
            print("This puzzle will unlock at exactly 9:00 PM (PST) tonight.")
            day = ""
            continue
        elif (element.get("href") == None):
            print("This puzzle is not available right now.")
            day = ""
            continue
        input_url = element["href"]
    print(input_url)
    pInput = requests.get(f"https://adventofcode.com{input_url}/input", headers=HEADERS).content
    inputParse = BeautifulSoup(pInput, "html.parser")
    print("Getting main input...")
    print(inputParse.get_text())

if __name__=="__main__":
    main()







# print(html.prettify())

# print(html.find_all("span", class_="calendar-day5"))
# print(html.select_one(".calendar-day5"))
# print(html)