select p.name, count(*) as count_of_visits
from person_visits as pv
join person as p
	on p.id = pv.person_id
group by p.name
having count(*) > 3;