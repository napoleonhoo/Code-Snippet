set -xe
cd ..

g++ -c RPC/RPC.cc -o RPC/RPC.o -I.

g++ -c RPC/rpc_client_debug.cc -o RPC/rpc_client_debug.o 
g++ RPC/RPC.o RPC/rpc_client_debug.o -o RPC/rpc_client_debug -fsanitize=address -fno-omit-frame-pointer -O1

g++ -c RPC/rpc_server_debug.cc -o RPC/rpc_server_debug.o 
g++ RPC/RPC.o RPC/rpc_server_debug.o -o RPC/rpc_server_debug -fsanitize=address -fno-omit-frame-pointer -O1