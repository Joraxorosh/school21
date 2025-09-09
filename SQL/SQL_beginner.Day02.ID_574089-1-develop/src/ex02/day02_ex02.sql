select coalesce(p.name, '-') as person_name, pv.visit_date, coalesce(pz.name, '-') as pizzeria_name
from person as p
full join (select *
		   from person_visits
		   where visit_date between '2022-01-01' and '2022-01-03') 
		   as pv
on p.id = pv.person_id
full join pizzeria as pz 
on pz.id = pv.pizzeria_id
order by person_name, visit_date, pizzeria_name