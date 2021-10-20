# status messages
DONE = 'DONE'
SUCCESS = 'SUCCESS'
FAILED = 'FAILED'


def printOperation(message):
    print('{:<40s}'.format(message), end="", flush=True)
