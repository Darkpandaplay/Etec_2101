



class WordReader
{
private:
    size_t file_len;
    std::ifstream fp;

public:
    WordReader();

    ~WordReader();

    std::string extractWord();

};

WordReader::WordReader()
{
    fp.open("../../media/american-words.txt.txt", std::ios::binary);
    fp.seekg(0, std::ios::end);
    file_len = fp.tellg();
}

WordReader::~WordReader()
{
    fp.close();
}

std::string WordReader::extractWord()
{
    int rando = std::rand() % file_len - 1;
    fp.seekg(rando, std::ios::beg);
    fp.seekg(-1, std::ios::cur);
    
    char boo = fp.peek();
    while (boo != ' ')
    {
        fp.seekg(-1, std::ios::cur);
        boo = fp.peek();
    }
    std::string read_word;
    std::getline(fp, read_word);
    return read_word;
}
