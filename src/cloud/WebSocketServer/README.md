Working with NodeJS WebSocket server locally

0. Install nodejs and npm first. https://nodejs.org/en/download/package-manager/
1. To install required libraries, type below command under the directory contains package.json.
2. npm install
3. Ready to go. 
4. node wsockServer.js
5. Some ubuntu versions blocks node binary usage. So you can also type nodejs or create a symlink under /usr/bin.
6. Change WSOCK_HOST with your PC IP and assign WSOCK_PORT as 7890 from Credentials.h to connect to server via device.

Working with NodeJS WebSocket server from cloud

0. Currently we have an AWS EC2 account where our server runs constantly.
   EC2 is an elegant way of running servers over the cloud but its free tier has only 1 year usage limit. 
   A domain name was set on current AWS EC2 instance's IP, to not require modifying IP on our running both device and user client .

