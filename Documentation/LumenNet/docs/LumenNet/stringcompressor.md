<span style="background-color: rgb(255, 255, 255);">![Oculus VR,
Inc.](RakNet_Icon_Final-copy.jpg){width="150" height="150"}</span>\
\
  ----------------------------
   StringCompressor overview
  ----------------------------

+--------------------------------------------------------------------------+
| <span class="RakNetBlueHeader">Encode and decode strings safely</span>\  |
| \                                                                        |
| The StringCompressor class, found in StringCompressor.h, will encode and |
| decode a given string in a safe fashion, protecting from overruns.       |
|                                                                          |
| Sender:                                                                  |
|                                                                          |
| const char \*str = "My string";\                                         |
| stringCompressor-&gt;EncodeString(str,TRUNCATION\_LENGTH,&bitStream,lang |
| uageId);                                                                 |
|                                                                          |
| Receiver:                                                                |
|                                                                          |
| char buffer\[TRUNCATION\_LENGTH\];\                                      |
| stringCompressor-&gt;DecodeString(buffer, TRUNCATION\_LENGTH,            |
| &bitStream, languageId);                                                 |
|                                                                          |
| The first parameter is the string to encode/decode. The second           |
| parameters is the maximum number of characters to read/write. If the     |
| string is longer than this, only that many bytes will be sent/read. The  |
| third parameter is the bitstream to write to or read from to. The last   |
| parameter indicates what character frequency table to use, which must be |
| the same on both systems.                                                |
|                                                                          |
| The string will be compressed using Huffman encoding based on the        |
| indicated frequency table, denoted by languageId. The default frequency  |
| table at index 0 is statically defined in StringCompressor.h with the    |
| varaible englishCharacterFrequencies. In order to add your own frequency |
| tables, call GenerateTreeFromStrings() with the desired language ID.     |
|                                                                          |
| If your application is using the CString class, you can enable support   |
| for this by defining \_CSTRING\_COMPRESSOR in StringCompressor.h.        |
|                                                                          |
| Similarly, if your application is using std::string, you can enable      |
| support for this by defining \_STD\_STRING\_COMPRESSOR in                |
| StringCompressor.h                                                       |
+--------------------------------------------------------------------------+

  -----------------------
   StringTable overview
  -----------------------

+--------------------------------------------------------------------------+
| <span class="RakNetBlueHeader">Predefine static strings to reduce        |
| bandwidth</span>\                                                        |
|                                                                          |
| The StringTable class is identical to the StringCompressor class, with   |
| the addition of the AddString function.                                  |
|                                                                          |
| void AddString(const char \*str, bool copyString);                       |
|                                                                          |
| str is the string to add.\                                               |
| copyString should be true if your string is not persistent, false if is  |
| statically in memory (only a pointer will be stored).                    |
|                                                                          |
| The AddString will check an internal array to see if this string has     |
| already been registered. If not, it will internally store a two byte     |
| identifier representing this string. Further sends using the StringTable |
| class will only send that two byte identifier, rather than the whole     |
| string, which is faster and takes less bandwidth if your string is 3 or  |
| more characters long. If you send a string which has not been added with |
| AddString(), the function acts the same as if you called                 |
| stringCompressor, but at the cost of 1 extra bit.                        |
|                                                                          |
| Both systems must have the same set of strings registered in advance, in |
| the same order, and both systems must use StringTable and                |
| StringCompressor in the corresponding send and receive calls. You cannot |
| mix and match the two.\                                                  |
+--------------------------------------------------------------------------+

  -----------------------------------------------
  ![](spacer.gif){width="8" height="1"}See Also
  -----------------------------------------------

+--------------------------------------------------------------------------+
| [Index](index.html)\                                                     |
| DS\_HuffmanEncodingTree.h\                                               |
+--------------------------------------------------------------------------+


