# Diffie Hellman
## Introduction
A careful eye may notice a hole with the mathematical outline of the cryptographic algorithms: we assume that both parties have both keys. This generates a new question: how do we, exactly, distribute the keys securely? In the past, often with more archaic algorithms, the set of keys were agreed upon prior to the exchange. However, in the digital age, this is not exactly a robust method of key distribution. Luckily, we have access to a particularly clever algorithm that allows us to exchange keys: Diffie Hellman. 
## 