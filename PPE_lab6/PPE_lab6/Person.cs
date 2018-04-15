using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PPE_lab6
{
    class Person
    {
       public string Name { get; set; }
       public string Surname { get; set; }
       public string Hobby { get; set; }
       public string Profession { get; set; }

        public Person(String name, String surname, string hobby, String profession)
        {
            Name = name;
            Surname = surname;
            Hobby = hobby;
            Profession = profession;
        }

    }
}
