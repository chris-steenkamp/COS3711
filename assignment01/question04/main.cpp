#include <QCoreApplication>
#include <QFile>
#include <QRegExp>
#include <QStringList>
#include <QTextStream>

static QTextStream cin(stdin);
static QTextStream cout(stdout);

static bool aFlag = false;
static bool bFlag = false;
static bool cFlag = false;
static bool dFlag = false;

void usage() {
    cout << "Usage: count [OPTION]... file1 [file2]... " << endl
         << "OPTION\tDescription" << endl
         << "  -a\tcount the number of words longer than 4 characters that start with a capital letter." << endl
         << "  -b\tcount the number of words that are hyphenated." << endl
         << "  -c\tcount the number of words that start and end on the same character." << endl
         << "  -d\tcount the number of words that do not start with a vowel." << endl
         << endl
         << "If no options are given it is assumed that all counts should be performed." << endl
         << flush;

    exit(1);
}

void error(QString message) {
    cout << "Error:"  << message << endl << flush;

    usage();
}

void fourOrLonger(QString input) {
    QRegExp r("\\b[A-Z]\\w{3}\\w+");
    int count = 0;
    int pos = 0;
    while ((pos = r.indexIn(input, pos)) != -1) {
        ++count;
        pos += r.matchedLength();
    }
    cout << "Number of words longer than 4 letters that start with a capital: " << count << endl << flush;
}

void hyphenatedWords(QString input) {
    QRegExp r("\\b\\w+-\\w+");
    int count = 0;
    int pos = 0;
    while ((pos = r.indexIn(input, pos)) != -1) {
        ++count;
        pos += r.matchedLength();
    }
    cout << "Number of hyphenated words: " << count << endl << flush;
}

void firstAndLast(QString input) {
    QRegExp r("\\b(\\w)\\w*(\\w)");
    int count = 0;
    int pos = 0;
    while ((pos = r.indexIn(input, pos)) != -1) {
        if (r.cap(1) == r.cap(2)) {
            ++count;
        }
        pos += r.matchedLength();
    }
    cout << "Number of words that start and end on the same letter: " << count << endl << flush;
}

void nonVowelBoundary(QString input) {
    QRegExp r("\\b(?![AEIOUaeiou])[a-zA-Z0-9-]+");
    int count = 0;
    int pos = 0;
    while ((pos = r.indexIn(input, pos)) != -1) {
        QString s = r.cap(0);
        ++count;
        pos += r.matchedLength();
    }
    cout << "Number of words that do not start with a vowel: " << count << endl << flush;
}

void processFlags(QString args) {
    QRegExp flags("([abcd])");
    int pos = 0;
    //For each character which matches in args, set the appropriate flag to true.
    //The assignment is OR'd to ensure that once flag is set, it cannot be unset.
    while ((pos = flags.indexIn(args, pos)) != -1) {
            aFlag |= (flags.cap(1) == "a");
            bFlag |= (flags.cap(1) == "b");
            cFlag |= (flags.cap(1) == "c");
            dFlag |= (flags.cap(1) == "d");

            pos += flags.matchedLength();
    }
}

void processFile(QString filename) {
    QFile file(filename);
    if (!file.open(QFile::ReadOnly)) {
        error(QString("Unable to open file %0").arg(filename));
    }

    QString fileData = file.readAll();
    fileData = fileData.remove(QRegExp("[^a-zA-Z0-9-\\s]"));

    cout << "***" << filename << "***" << endl;

    if (aFlag) {
        fourOrLonger(fileData);
    }

    if (bFlag) {
        hyphenatedWords(fileData);
    }

    if (cFlag) {
        firstAndLast(fileData);
    }

    if (dFlag) {
        nonVowelBoundary(fileData);
    }

    cout << endl << flush;

    file.close();
}

int main(int argc, char *argv[])
{
    if (argc == 1) {
        usage();
    }

    //Matches flags provided as both -a -b and -ab
    QRegExp flags("^-([abcd]+)$");
    QStringList fileList;

    for (int i = 1; i < argc; ++i) {
        //Arguments are interpreted as either a flag or a filename
        if (flags.exactMatch(argv[i])) {
            processFlags(flags.capturedTexts()[1]);
        }
        //Error on anything that looks like a flag but is not valid
        else if (QString(argv[i]).contains('-')) {
            error(QString("Invalid option %0").arg(argv[i]));
        }
        //Otherwise, assume the argument is a file
        else {
            fileList << argv[i];
        }
    }

    if (fileList.isEmpty()) {
        error("At least one filename must be specified.");
    }

    //If none of the flags are set then we set them to all be true
    if (!aFlag && !bFlag && !cFlag && !dFlag) {
        aFlag = true;
        bFlag = true;
        cFlag = true;
        dFlag = true;
    }

    for (int i = 0; i < fileList.count(); ++i) {
        processFile(fileList[i]);
    }

    return 0;
}
