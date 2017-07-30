import sys
import subprocess
import os

testString = 'Huffmans Coding()123;'
inputFile = 'inputNoseTest'
outputFile = 'outputNoseTest'
decodedFile = 'decodedNoseTest'
encoded = b'\xff\xf8_\xc9\xbf\xdf\xf7?\x7f\x93\xfc\xf9\xf7\xde\xf9\xff\x00'


def testMake():
    child = subprocess.Popen('make')
    streamData = child.communicate()[0]
    assert child.returncode == 0


def testHuffmanString():
    bashCommand = './huffman -s \"' + testString + '\" ' + outputFile
    subprocess.call(bashCommand, shell=True)
    file = open(outputFile, 'rb')
    line = file.readline()
    file.close()
    os.remove(outputFile)
    os.remove(outputFile + '_key')
    assert line.lower().strip() == encoded.lower().strip()


def testHuffmanFileEncoding():
    file = open(inputFile, 'w')
    file.write(testString)
    file.close()

    bashCommand = './huffman -e \"' + inputFile + '\" \"' + outputFile + '\"'
    subprocess.call(bashCommand, shell=True)

    file = open(outputFile, 'rb')
    line = file.readline()
    file.close()

    os.remove(inputFile)
    os.remove(outputFile)
    os.remove(outputFile + '_key')

    assert line.lower().strip() == encoded.lower().strip()


def testHuffmanDecoding():
    bashCommand = './huffman -s \"' + testString + '\" ' + outputFile
    subprocess.call(bashCommand, shell=True)
    bashCommand = './huffman -d ' + outputFile + ' ' + decodedFile + \
        ' ' + outputFile + '_key'
    subprocess.call(bashCommand, shell=True)

    file = open(decodedFile, 'r')
    line = file.readline()

    os.remove(outputFile)
    os.remove(outputFile + '_key')
    os.remove(decodedFile)

    assert line == testString


def testAuthors():
    bashCommand = './huffman --authors'
    returnCode = subprocess.call(bashCommand, shell=True)
    assert returnCode == 0

def testMakeClear():
    child = subprocess.Popen('make clear', shell=True)
    streamData = child.communicate()[0]
    assert child.returncode == 0