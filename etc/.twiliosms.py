import twilio
from twilio.rest import Client
import sys

if len(sys.argv) != 7:
    sys.exit(5)

account_sid = str(sys.argv[1])
auth_token = str(sys.argv[2])
cli_num = str(sys.argv[3])
code = str(sys.argv[4])
header = str(sys.argv[5])
usr_num = str(sys.argv[6])

autho_mess = header + code

client = Client(account_sid, auth_token)

message = client.messages.create(
    to=usr_num, 
    from_=cli_num,
    body=autho_mess
)


