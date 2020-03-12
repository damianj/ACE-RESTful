import json
from jinja2 import Environment, PackageLoader, select_autoescape


with open("docs.json", mode="r") as docs_json:
    api_docs = json.load(docs_json)

env = Environment(
    loader=PackageLoader('generate-docs', 'templates'),
    autoescape=select_autoescape(['html', 'xml'])
)

template = env.get_template('docs-content-template.html')
pre_content = """@Master['base.sshtml']

@Section['PageTitle']
ACE API Docs
@EndSection

@Section['Content']"""

post_content = """@EndSection"""

with open("./Views/docs.sshtml", mode="w") as docs_sshtml:
    docs_sshtml.write(template.render(api_docs=api_docs, pre_content=pre_content, post_content=post_content))
