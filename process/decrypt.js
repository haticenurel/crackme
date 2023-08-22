const fs = require('fs');

// Read the encrypted file
const encryptedData = fs.readFileSync('/Users/haticenurel/Documents/GitHub/crackme/target/src/encrypted_zipped_text.enc');
const key = 'K'; // XOR encryption key

// XOR decryption function
function xorDecrypt(data, key) {
    return data.map(byte => byte ^ key.charCodeAt(0));
}

// Decrypt the data
const decryptedData = xorDecrypt(encryptedData, key);

// Write the decrypted data to a new file
fs.writeFileSync('/Users/haticenurel/Documents/GitHub/crackme/process/decrypted_zipped_text.txt', Buffer.from(decryptedData));

console.log('Decryption complete.');
