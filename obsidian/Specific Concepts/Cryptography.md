# Cryptography
## Summary
TODO: Rewrite this into paragraph form because bullets are kind of ugly. 

Cryptography is the discipline concerning the creation, decryption, 

- Cryptography is the study of making and breaking codes. 
- It is a distinctly computational discipline: these codes are made and broken using computers. 
- It is a distinctly mathematical discipline: cryptographic algorithms often use special problems within higher level mathematics. 
- In the modern day, there are a few important use cases for cryptography: 
	- Public-key encryption: are exchanges over the internet (or conversations) secure, and unreadable by other third parties? Basically, can we prevent digital espionage? 
	- Database encryption: is the MASSIVE amount of data stored on the internet, including important things like healthcare, banking information, and more, securely stored? Can it be easily stolen? 
- In general, cryptographic algorithms work as follows: 
	- First, find a difficult mathematical problem. 
		- Define a sufficiently difficult mathematical problem as a problem that is REALLY HARD to solve (as in bordering on impossible), but VERY EASY to solve if you have a certain piece of information. Call this the key. 
	- Next, convert parts of this mathematical problem to the corresponding part of the algorithm. 
		- The message that we want to send/recieve is called the plaintext. 
		- The encrypted version of this message that we actually transmit over the internet is called the ciphertext. 
		- The aforementioned keys used to decrypt the ciphertext is called the public key and the private key. 
			- The public key is freely available, and transmit with the ciphertext. 
			- The private key is secret between the two parties. 
	- We combine this problem to conform to some definition of a scheme
		- [[KEM]]
- There are a few algorithms considered to be state of the art within cryptography
	- [[RSA]]
		- This is the oldest, and most commonly used encryption scheme. 
		- We use the "prime factorization" problem
		- Combined with Diffie-Hellman for public key encryption
	- [[ECC]]
		- This is a newer, more efficient, and increasingly used encryption scheme
		- We use the "elliptic curve" problem
		- Inherently compatible with public key encryption
## Draft
