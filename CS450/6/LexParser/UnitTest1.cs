using System;
using Xunit;
using System.IO;

namespace Lexparser.test
{
    public class UnitTest1
    {
        /*checks to see if proper value of assignment*/
        [Fact]
        public void CheckAssignment1()
        {
            string text = "=";
            Homework6.Program.in_fp = new StreamReader(new MemoryStream(
            System.Text.Encoding.ASCII.GetBytes(text))); //Stream reader probably not the best option in hindsight but WE'VE COME SO FAR 
            Homework6.Program.getChar();
            int token = Homework6.Program.lex();
            int actual = Homework6.Constants.ASSIGN_OP;
            Assert.Equal(actual, token);
        }
        /*Checks to see if proper value of lex not in language*/
        [Fact]
        public void CheckUknown1()
        {
            string text = "<";
            Homework6.Program.in_fp = new StreamReader(new MemoryStream(
            System.Text.Encoding.ASCII.GetBytes(text)));
            Homework6.Program.getChar();
            int token = Homework6.Program.lex();
            int actual = Homework6.Constants.LESS_THAN;
            Assert.Equal(actual, token);
        }



        /* Much messier than I would like, but didnt know how else to do without rewriting everything
         * Inputs the string, and then calls lex the same amount of times as the length of the string,
         and stores the values of the tokens at each iteration*/
        [Fact]
        public void CheckSentence1()
        {
            string text = "AGreater = A > B;";
            Homework6.Program.in_fp = new StreamReader(new MemoryStream(
            System.Text.Encoding.ASCII.GetBytes(text)));
            Homework6.Program.getChar();
            int actual = Homework6.Constants.IDENT;
            int actual1 = Homework6.Constants.ASSIGN_OP;
            int actual2 = Homework6.Constants.IDENT;
            int actual3 = Homework6.Constants.GREATER_THAN;
            int actual4 = Homework6.Constants.IDENT;
            int actual5 = Homework6.Constants.EOL;

            int[] mylist = new int[] { actual, actual1, actual2, actual3, actual4, actual5 };
            int[] fromprogram = new int[mylist.Length];
            for (int i = 0; i < mylist.Length; ++i)
            {
                fromprogram[i] = Homework6.Program.lex();
            }

            Assert.Equal(mylist, fromprogram);
        }


        //Checking to see an empty string is processed correctly 
        [Fact]
        public void Checkempty()
        {
            string text = "";
            Homework6.Program.in_fp = new StreamReader(new MemoryStream(
            System.Text.Encoding.ASCII.GetBytes(text)));
            Homework6.Program.getChar();
            int token = Homework6.Program.lex();
            int actual = Homework6.Constants.EOF;
            Assert.Equal(token, actual);
        }
        //Checking to see if an ioexception is thrown when read from an empty file
        [Fact]
        public void Checkexception()
        {
            string text = "";
            Homework6.Program.in_fp = new StreamReader(new MemoryStream(
            System.Text.Encoding.ASCII.GetBytes(text)));
            Homework6.Program.getChar();
            Homework6.Program.lex();
            try
            {
                int token = Homework6.Program.lex();
            }
            catch (Exception e)
            {
                Assert.IsType<IOException>(e);
            }
        }
        //checking a longer senctence also correctly gets identified
        [Fact]
        public void CheckSentence2()
        {
            string text = "Result = A == B;";
            Homework6.Program.in_fp = new StreamReader(new MemoryStream(
            System.Text.Encoding.ASCII.GetBytes(text)));
            Homework6.Program.getChar();

            int actual = Homework6.Constants.IDENT;
            int actual1 = Homework6.Constants.ASSIGN_OP;
            int actual2 = Homework6.Constants.IDENT;
            int actual3 = Homework6.Constants.EQUALITY_OP;
            int actual4 = Homework6.Constants.IDENT;
            int actual5 = Homework6.Constants.EOL;


            int[] mylist = new int[] { actual, actual1, actual2, actual3, actual4, actual5 };
            int[] fromprogram = new int[mylist.Length];
            for (int i = 0; i < mylist.Length; ++i)
            {
                fromprogram[i] = Homework6.Program.lex();
            }

            Assert.Equal(mylist, fromprogram);
        }
        //Checking to see if the . properly registers as an unkown
        [Fact]
        public void CheckUknown2()
        {
            string text = "==";
            Homework6.Program.in_fp = new StreamReader(new MemoryStream(
            System.Text.Encoding.ASCII.GetBytes(text)));
            Homework6.Program.getChar();
            int token = Homework6.Program.lex();
            int actual = Homework6.Constants.EQUALITY_OP;
            Assert.Equal(actual, token);
        }
        //Checking to see if my equivalence operator is properly identified
        [Fact]
        public void CheckAssignment2()
        {
            string text = "!=";
            Homework6.Program.in_fp = new StreamReader(new MemoryStream(
            System.Text.Encoding.ASCII.GetBytes(text))); //Stream reader probably not the best option in hindsight but WE'VE COME SO FAR 
            Homework6.Program.getChar();
            int token = Homework6.Program.lex();
            int actual = Homework6.Constants.INEQUALITY_OP;
            Assert.Equal(actual, token);
        }

    }
}