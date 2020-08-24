txt_file = open('site5.dat','w') 
from datetime import timedelta  
from datetime import date
d1= date(2010, 10, 16)
s = 1
site = 1
name = "Examples of the concept include Integration and polymorphism : degree of autonomy of individual versus integration of specialized individuals, relative degrees of fitness Boardman and Cheetham, 1973; Schopf, 1973; Bates and Kirk, 1985; Pitelka and Ashmun, 1985; Mackie, 1986"
#1|No|TestSite1|1-100|2019/02/04|2019/11/29|10|rong@datafax.com|dundas 501|AIA|905888888|407888888|Rong|mailto:rong@datafax.com|2019/04/01|1.0|2019/04/10|5.ddd|2019/06/18|2.0|2019/07/16|3.333|2019/11/19|4sa
names = name.split(" ")
name_size = len(names)
name_index = 0
for i in range(5):
    print(i,"--------")
    
    site_str = str(i+1) + "|No|CRF Site - "
    site_str += str(site) + "|" + str(s) + "-" + str(s+99) +"|" + d1.strftime("%Y/%m/%d") + "|"
    site_str += (d1 +  timedelta(days=10) ).strftime("%Y/%m/%d") +"|10|rong@datafax.com|"
    site_str +=  names[name_index] + "|AIA|905888888|407888888|Rong|mailto:rong@datafax.com|"
    site_str +=  (d1 +  timedelta(days=1) ).strftime("%%Y/%m/%d")
    site_str +=  "|1.0|" + (d1 +  timedelta(days=2) ).strftime("%Y/%m/%d") + "|5.ddd|" + (d1 +  timedelta(days=3) ).strftime("%Y/%m/%d")
    site_str +=  "|2.0|" + (d1 +  timedelta(days=4) ).strftime("%Y/%m/%d") + "|3.333|" + (d1 +  timedelta(days=10) ).strftime("%Y/%m/%d") + "|4.sa\n"
    txt_file.write(site_str )
    s+=100
    site +=1
    d1 +=  timedelta(days=1) 
    name_index+=1
    if name_index == name_size:
        name_index = 0
print ("done")
txt_file.close()