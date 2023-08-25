# Function to Cipher Shift
# Parameter cipher (array) and key (int)
def shiftcipher(cipher, key):
    # Create a local cipher array
    cipher2 = [0]*len(cipher)
    for i in range(len(cipher2)):
        cipher2[i] = cipher[i]

    # For each char in the string, do the cipher shift.
    for j in range(len(cipher2)):
        cipher2[j] = (ord(cipher[j])-ord(‘a’)) + key
        cipher2[j] %= 26
        cipher2[j] += ord('a')
        cipher2[j] = chr(cipher2[j])

    # Convert it back to string, taken from Google.
    newCipher = convert(cipher2)

    return newCipher

# Function to Affine Cipher
# Needs slope a (int), y intercept b(int), and cipher (char array)
def affinecipher(cipher, a, b):
    # Create a local cipher array
    cipher2 = [0]*len(cipher)
    for i in range(len(cipher2)):
        cipher2[i] = cipher[i]

    # For each char in string, do affine cipher
    for x in range(len(cipher)):
        cipher2[x] = (ord(cipher2[x])-ord('a'))
        cipher2[x] = ((cipher2[x] * a) + b) % 26
        cipher2[x] += ord('a')
        cipher2[x] = chr(cipher2[x])

    # convert the array back to string, taken from Google
    newCipher = convert(cipher2)
    return newCipher

# Function to Affine Cipher
# Needs slope a (int), y intercept b(int), and cipher (char array)
def daffinecipher(cipher, a, b):
    # Create a local cipher array
    cipher2 = [0]*len(cipher)
    for i in range(len(cipher2)):
        cipher2[i] = cipher[i]

    # For each char in string, do affine cipher
    for x in range(len(cipher)):
        cipher2[x] = (ord(cipher2[x])-ord('a'))
        cipher2[x] = ((cipher2[x] * modInverse(a, 26) + b) % 26)
        cipher2[x] += ord('a')
        cipher2[x] = chr(cipher2[x])

    # convert the array back to string, taken from Google
    newCipher = convert(cipher2)
    return newCipher

# Function that finds mod inverse.
def modInverse(A, M):
    for X in range(1, M):
        if (((A % M) * (X % M)) % M == 1):
            return X
    return -1

# Function taken from Google to convert a char array into String.
def convert(s):
    new = ""
    for x in s:
        new += x
    return new

def main():
    # All string to be encrypted/decrypted
    string = "ftueueftqnussqefftueoxmeetmeqhqdnqqz"
    to_array = [char for char in string]
    string2 = "kbzamghppxatoxhgermphmtlahixyneerbybgwtmabkwlhhg"
    to_array2 = [char for char in string2]
    string3 = "sibuovezdgbdfmtuqdwmnhmrgwxuxagsyrgwdfmtuqdwmnhmfeobgszdmmroifggnowmuzxfsfudfgsqfdog"
    to_array3 = [char for char in string3]
    to_temparray3 = to_array3
    string4 = "welcometocryptographyclasshopeyoufindbigprizeswhiledoingyourhomework"
    to_array4 = [char for char in string4]

    # Cipher Question based on number
    # Used to brute force find key
    #for x in range(26):
        #cipher = shiftcipher(to_array, x)
    cipher = shiftcipher(to_array, 14)

    # Used to brute force find key
    #for x in range(26):
        #cipher2 = shiftcipher(to_array2, x)
    cipher2 = shiftcipher(to_array2, 7)

    #Used to brute force find the decryption key for cipher 3
    #value = [1, 25, 9, 21 ,15, 19, 23]
    #for i in value:
        #for j in range(26):
            #print(i, " ", j)
            #cipher34 = daffinecipher(to_array3, i, j)
            #print(cipher34)
    cipher3 = daffinecipher(to_array3, 15, 24)
    cipher4 = affinecipher(to_array4, 11, 8)

    # Answers
    print("Cipher 1: ", cipher)
    print("Cipher 2: ", cipher2)
    print("Cipher 3: ", cipher3)
    print("Cipher 4: ", cipher4)
main()
