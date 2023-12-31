# RSA
## General Information
RSA is the most important encryption scheme to modern cryptography. It was the first robust and publicly distributed encryption algorithm and has been in use since its inception in the late 20th century. 
## Mathematical Definition
#### Prime Factorization
RSA operates within the field of Number Theory. To guarantee security, it utilizes the prime factorization problem, which takes advantage of the fact that it is nigh unto impossible to factor a really large composite number unless you are already given one of the prime factors.  RSA takes this problem and puts it on steroids by utilizing very large numbers (often with hundreds or thousands of digits). 
#### Key Generation
First, we pick two very large numbers $p, q \in \mathbb{Z}$: 
$$ p, q \in \mathbb{Z} \text{ (and very large) } $$
$$ n := pq$$
Then, we generate a number $e$ using this huge number $n$. Note that $\lambda$ is any totient function, usually chosen as Carmichael's totient but sometimes Euler's. A totient function is any function that counts up the amount of prime numbers to an integer $n \in \mathbb{Z}^+$. 
$$ 2 \leq e \leq \lambda(n) \text{ and } \text{gcd}(e, \lambda(n)) = 1$$
$e$ can be chosen from random with the parameters above. Randomness is an extremely important tool within cryptography. Note that it is mathematically dubious to pick a number at random but the threat this poses to literally any mathematical operation that is not purely theoretical with no consequences is trivial. We set the public key to be distributed freely as $(n, e)$. Finally, we can generate the private key $d$ as follows: 
$$ d := e^{-1} \mod{\lambda(n)} $$
All of this satisfies the first requirement of [[KEM]]: key generation. 
#### Encapsulation/Encryption
We are now ready to encrypt a message. First, we have to take the given message and hash the message; in other words, turn it into numbers. 

Hashing the message has the secondary benefit of obfuscating the method enough such that you can't derive the original message. While this may seem counterintuitive, consider the case that we want to simply *verify* a message rather than send it. By hashing the message, even if a third party were to get access to the hash somehow, they would not be able to use it in any way. Password verification, for example, utilizes hashes to this effect. However, if we do not wish to obfuscate the message, we can use a simple hash such as Base64 that can be inverted. 

For mathematical purposes, define the hashing function $h: A \to \mathbb{Z}$ where $A$ is the set containing the message.
$$ m := h(\text{message})$$
$$ c := m^e\mod{n} \text{  where } 0 \leq m < n$$
We call $c$ the ciphertext, which we distribute in this case. Note that anyone can generate the ciphertext, as long as they have the message they wish to encrypt and the public key they wish to use. 
#### Decapsulation/Decryption
After encrypting the message, we are now going to decrypt the message. Remember that as the decrypting party, we have access to three variables: 
1. The ciphertext, $c$
2. The public key, $(n, e)$. 
3. The private key, $d$. 
Also remember that the goal of the algorithm is to derive $m$, the original hashed message. RSA allows us to compute this cleverly:  
$$ c^d \equiv {m^e}^d \equiv m \mod{n}$$
Notice that we did not generate $m$; rather, we found $m \mod{n}$. However, because $0 \leq m < n$, $m \mod{n} = m$. We have finished decrypting our message, upon which we can either de-hash or verify. 

You may have noticed a flaw with the above appraisal: we assume that both parties already have the public and private keys. How, exactly, do we distribute the keys in such a way? For that, we have the [[Diffie Hellman]] algorithm. 
## Use Cases
