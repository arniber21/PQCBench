# RSA
## General Information
The most prominent cipher in modern cryptography, [[RSA]] (named after its architects, Rivest-Shamir-Adleman), utilizes the *factoring into primes problem*, which considers the prime factorization of very large numbers. The scheme is named for the three scientists who devised it at the Massachusetts Institute of Technology in 1978. We define the factorization problem as follows: given a positive integer $x \in \mathbb{Z}^+$, find the unique set of prime numbers $p_1, p_2, p_3, \cdots p_n$ and integer exponents $k_1, k_2, k_3,\cdots,k_n$ such that $x = p_1^{k_1}p_2^{k_2}p_3^{k_3} \cdots p_n^{k_n}$. Interestingly, it has been mathematically proven that there is *no efficient way* to factor large numbers; even the fastest methods are little more effective than trial and error. 

However, the factorization problem becomes trivial with a crucial bit of information: just one of these factors and an associated exponent. Given such a pair, we may simply divide the factor by x: $p^k \cdot x^{-1}$ in order to calculate the rest of the factorization trivially. Logically, then, [[RSA]] creates a cryptosystem using the prime factorization problem as defined below.  
## Mathematical Definition
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