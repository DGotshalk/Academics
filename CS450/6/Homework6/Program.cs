using System;
using System.IO;


namespace Homework6
{
    public static class Constants
    {
        public const int LETTER = 0;
        public const int DIGIT = 1;
        public const int UNKNOWN = 99;
        /* Token codes */
        public const int INT_LIT = 10;
        public const int IDENT = 11;
        public const int ASSIGN_OP = 20;
        public const int EQUIV_OP = 27;
        public const int ADD_OP = 21;
        public const int SUB_OP = 22;
        public const int MULT_OP = 23;
        public const int DIV_OP = 24;
        public const int LEFT_PAREN = 25;
        public const int RIGHT_PAREN = 26;
        public const int LESS_THAN = 30;
        public const int GREATER_THAN = 31;
        public const int EQUALITY_OP = 32;
        public const int INEQUALITY_OP = 33;
        public const int EOL = -2;
        public const int EOF = -1;
    }
    public static class Program
    {
        static int charClass;
        static char[] lexeme = new char[100];
        static char nextChar;
        static int lexLen;
        static int token;
        static char prevChar = ' ';
        public static int nextToken;
        public static StreamReader in_fp;
        static string filepath;
        static void Main(string[] args)
        {
            //Console.WriteLine("Please enter the path to the file to parse");
            //filepath = Console.ReadLine();
            //FileStream f = new FileStream(filepath, FileMode.Open);
            FileStream f = new FileStream("../../front.in", FileMode.Open);
            in_fp = new StreamReader(f);
            if (in_fp == null)
            {
                Console.WriteLine("Cannot open file front.in");
            }
            else
            {
                Console.WriteLine("1 Hit enter for input");
                getChar();
                while (nextToken != Constants.EOF)
                {
                    if (nextToken == Constants.EOL)
                    {
                        Console.WriteLine("Hit enter for input");
                        Console.ReadLine();
                    }
                    lex();
                    //write the functions 
                }
            }
            Console.ReadLine();
            in_fp.Close();
            in_fp.Dispose(); //I REMEMBERED
            f.Close();
        }
        //adds a character to the output string 
        static void addChar()
        {
            if (lexLen <= 98)
            {
                lexeme[lexLen++] = nextChar;
                lexeme[lexLen] = '\0';
            }
            else
                Console.WriteLine("Error - lexeme is too long");
        }


        //gets a single character from the text file and determines the class of the character 
        public static void getChar()
        {
            int end_check = in_fp.Read();


            if (end_check != Constants.EOF)
            {
                nextChar = (char)end_check;


                if (char.IsLetter(nextChar))
                    charClass = Constants.LETTER;
                else if (char.IsNumber(nextChar))
                    charClass = Constants.DIGIT;
                else if (nextChar == '\r' || nextChar == '\n')
                {
                    charClass = Constants.EOL;
                }
                else
                {

                    charClass = Constants.UNKNOWN;
                }
            }
            else { 
          
            nextChar = '\0';
            charClass = Constants.EOF;
        }
        }

        //Skips space values
        static void getNonBlank()
        {
            while (char.IsWhiteSpace(nextChar))
            {

                getChar();
            }
        }



        //This is the function that ends up deciding how the classification of the the char will effect output
        public static int lex()
        {
            lexLen = 0;

            getNonBlank();
            if (charClass == Constants.LETTER) {
                addChar();
                getChar();
                while (charClass == Constants.LETTER || charClass == Constants.DIGIT)
                {
                    addChar();
                    getChar();
                }
                nextToken = Constants.IDENT;
            }


            else if (charClass == Constants.DIGIT) {
                addChar();
                getChar();
                while (charClass == Constants.DIGIT)
                {
                    addChar();
                    getChar();
                }
                nextToken = Constants.INT_LIT;
            }

            else if (charClass == Constants.UNKNOWN) {
                if ((nextChar == '=' || nextChar == '!') && prevChar == ' ') // This case pops if we initially see any characters we know might start double strings. 
                {
                    prevChar = nextChar;
                    addChar();

                    getChar();

                    if (nextChar == '=') // we see that our double character condition is met , "!=" or "=="
                    {
                        addChar();
                        if (prevChar == '!')
                        {
                            nextToken = Constants.INEQUALITY_OP;
                        }
                        else if (prevChar == '=')
                        {
                            nextToken = Constants.EQUALITY_OP;
                        }
                        getChar();
                    }
                    else
                    {
                        nextToken = Constants.ASSIGN_OP;
                        //getChar();
                    }
                    prevChar = ' ';
                }
                else
                {
                    lookup(nextChar);
                    getChar();
                }
            }
      
 
            else if (charClass == Constants.EOL){
                addChar();
                nextToken = Constants.EOL;
                lexeme[0] = 'E';
                lexeme[1] = 'O';
                lexeme[2] = 'L';
                getChar();

            }
            else if (charClass == Constants.EOF) {
                addChar();
                nextToken = Constants.EOF;
                lexeme[0] = 'E';
                lexeme[1] = 'O';
                lexeme[2] = 'F';

            }
            /* End of switch */
            Console.Write("Next Token is: ");
            Console.Write(nextToken);
            Console.Write(" Next lexeme is: ");
            Console.WriteLine(lexeme);
            lexeme = new char[100];
            return nextToken;
        }

        //This lookup function gets called when some value gets seen that is not a digit, alphabetical character, or the newline or EOF
        static int lookup(char ch)
        {
            switch (ch)
            {
                case '(':
                    addChar();
                    nextToken = Constants.LEFT_PAREN;
                    break;
                case ')':
                    addChar();
                    nextToken = Constants.RIGHT_PAREN;
                    break;
                case '+':
                    addChar();
                    nextToken = Constants.ADD_OP;
                    break;
                case '-':
                    addChar();
                    nextToken = Constants.SUB_OP;
                    break;
                case '*':
                    addChar();
                    nextToken = Constants.MULT_OP;
                    break;
                case '/':
                    addChar();
                    nextToken = Constants.DIV_OP;
                    break;
                case '=':
                    addChar();
                    nextToken = Constants.ASSIGN_OP;
                    break;
                case '~':
                    addChar();
                    nextToken = Constants.EQUIV_OP;
                    break;
                case ';':
                    addChar();
                    nextToken = Constants.EOL;
                    lexeme[0] = 'E';
                    lexeme[1] = 'O';
                    lexeme[2] = 'L';
                    break;
                case '<':
                    addChar();
                    nextToken = Constants.LESS_THAN;
                    break;
                case '>':
                    addChar();
                    nextToken = Constants.GREATER_THAN;
                    break;
                default:
                    addChar();
                    nextToken = Constants.UNKNOWN;
                    break;
            }
            return nextToken;
        }
    }
}

