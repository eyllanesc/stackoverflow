import os
import json

def create_arguments(search_item, locations):
	program = 'scrapy'
	dir_path = os.path.dirname(os.path.abspath(__file__))
	directory = os.path.join(dir_path, 'scrape')
	d = {"search_item": search_item, "locations": locations}
	argument = 'parameters={}'.format(json.dumps(d))
	return directory, program, ['crawl', 'yellow', "-a", argument]