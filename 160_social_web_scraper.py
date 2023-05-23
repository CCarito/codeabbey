import re
import requests
import time

def download_page(url):
    response = requests.get(url)
    return response.text

def extract_links(page):
    pattern = r'<a href="([^"]+)">'
    return re.findall(pattern, page)

def extract_last_name(page):
    pattern = r'<span class="last-name">([^<]+)</span>'
    match = re.search(pattern, page)
    if match:
        return match.group(1)
    return None

def extract_net_worth(page):
    pattern = r'<span class="net-worth">(\d+)</span>'
    match = re.search(pattern, page)
    if match:
        return int(match.group(1))
    return 0

def process_social_network(last_name):
    initial_url = 'http://fake-social-network-url.com/john-doe.html'
    visited_pages = set()
    total_net_worth = 0

    queue = [(initial_url, last_name)]
    while queue:
        url, name = queue.pop(0)
        if url in visited_pages:
            continue

        visited_pages.add(url)
        page = download_page(url)
        page_last_name = extract_last_name(page)
        if page_last_name and page_last_name.lower() == name:
            total_net_worth += extract_net_worth(page)

        links = extract_links(page)
        for link in links:
            if link.startswith('./'):
                link = url.rsplit('/', 1)[0] + link[2:]
            queue.append((link, name))

    return total_net_worth

last_name = input().strip().lower()
net_worth = process_social_network(last_name)
print(net_worth)
