using System;

namespace Student
{

    class Student
    {
        private int admno;
        private String sname;
        float eng, math, science;
        float total;
        float ctotal()
        {
            return eng + math + science;
        }
        public void takeData()
        {
            Console.WriteLine("Enter admission number ");
            admno = Convert.ToInt32(Console.ReadLine());
            Console.WriteLine("Enter student name ");
            sname = Console.ReadLine();
            Console.WriteLine("Enter marks in english, math, science ");
            eng = Convert.ToInt32(Console.ReadLine());
            math =  Convert.ToInt32(Console.ReadLine());
            science = Convert.ToInt32(Console.ReadLine());
            total = ctotal();
        }
        void showData()
        {
            Console.WriteLine("Admission number: " + admno);
            Console.WriteLine("Student name: " + sname);
            Console.WriteLine("English: " + eng);
            Console.WriteLine("Math: " + math);
            Console.WriteLine("Science: " + science);
            Console.WriteLine("Total: " + total);
        }
        public static void Main(String[] args)
        {
            Student student = new Student();
            student.takeData();
            student.showData();
        }
    }
}
