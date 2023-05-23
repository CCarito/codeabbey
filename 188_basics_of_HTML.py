def create_html_page(secret_value):
    html_content = '''<html>
    <head>
        <title>Basics of HTML demo</title>
    </head>
    <body>
        <p>Secret value is <b>{}</b>.</p>
        <p>Read more at
            <a href="http://www.codeabbey.com/index/task_view/basics-of-html">this task</a>.
        </p>
    </body>
</html>'''.format(secret_value)

    file_name = 'simple.html'
    with open(file_name, 'w') as file:
        file.write(html_content)

    return 'http://codeabbey.github.io/data/simple.html'

# Read the secret value from input
secret_value = input()

# Create and upload the HTML page, and get the URL
url = create_html_page(secret_value)

# Print the URL
print(url)
