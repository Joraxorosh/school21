select p1.name as person_name1, p2.name as person_name2, p1.address as common_adress
from person as p1
join person as p2
on p1.id > p2.id and p1.address = p2.address
order by 1, 2, 3