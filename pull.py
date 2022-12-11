import os
from dotenv import load_dotenv
import requests
from bs4 import BeautifulSoup
import re
import shutil

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
        return

    content = result.content

    html = BeautifulSoup(content, "html.parser")

    day = ""
    input_url = ""
    while day == "":
        day = input("Day: ")
        element = html.find_all(["span", "a"], {'class': re.compile(rf'^calendar-day{day}')})[-1]
        print(element["class"])
        if (element.findChild("span", {"id": "calendar-countdown"}) != None):
            print("This puzzle will unlock at exactly 9:00 PM (PST) tonight.")
            day = ""
            continue
        elif (element.get("href") == None):
            print("This puzzle is not available right now.")
            day = ""
            continue
        input_url = element["href"]

    print("Getting main input...")
    mainInput = requests.get(f"https://adventofcode.com{input_url}/input", headers=HEADERS).content
    mainInput = BeautifulSoup(mainInput, "html.parser")

    dir = os.path.join(os.getcwd(), f"Day {day}")
    print("Creating directory...")
    if os.path.isdir(dir):
        print(f"Directory {dir} already exists... Skipping creation")
    else:
        os.mkdir(dir)
        print(f"Directory {dir} created")
    
    print("Creating main input file...")
    if (os.path.exists(os.path.join(dir, "main.in"))):
        print(f"File {dir}/main.in already exists... Skipping creation")
    else:
        with open(os.path.join(dir, "main.in"), "w") as f:
           f.writelines(mainInput.get_text().rstrip())
           print(f"File {dir}/main.in created")
    
    print("Creating test input file...")
    if (os.path.exists(os.path.join(dir, "test.in"))):
        print(f"File {dir}/test.in already exists... Skipping creation")
    else:
        open(os.path.join(dir, "test.in"), "w")
        print(f"Testing file {dir}/test.in created")

    while True: 
        name = input("Name the puzzle: ")

        if (os.path.exists(os.path.join(dir, f"{name}P1.cpp")) or os.path.exists(os.path.join(dir, f"{name}P2.cpp"))):
            print("A file with that name already exists")
            continue
        else:
            try:
                shutil.copy(os.path.join(os.getcwd(), "template.txt"), os.path.join(dir, f"{name}P1.cpp"))
                shutil.copy(os.path.join(os.getcwd(), "template.txt"), os.path.join(dir, f"{name}P2.cpp"))
            except:
                print("Error: the template file 'template.txt' does not exist in the current working directory. This file is required to setup the base template.")
                continue
            print("Code files for Parts 1 and 2 created.")
            break
    print("Finished.")

if __name__=="__main__":
    main()