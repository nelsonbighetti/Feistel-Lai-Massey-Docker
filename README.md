# Feistel-Lai-Massey-Docker

This utility allows you to encrypt and decrypt files using a cryptosystem, consisting of two cycles of the Lay-Massey cryptosystem and two cycles of the Feistel cryptosystem.

Key lenght is fixed and must be 4 symbols. 

Usage: 
1. Run container executing script "run_container.sh"
2. Encryption: crypt.sh -enc <path to file> <path to key> <path to output file> 
3. Decryption: crypt.sh -dec <path to encrypted file> <path to key> <path to decrypted file> 

All paths must be absolute. 

Docker Hub: 
https://hub.docker.com/r/dockodocker/flm_crypto
