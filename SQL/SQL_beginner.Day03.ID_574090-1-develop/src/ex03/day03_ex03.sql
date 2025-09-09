(select pz.name as pizzeria_name
 from person as p
 join person_visits as pv 
 	on pv.person_id = p.id
 join pizzeria as pz 
 	on pz.id = pv.pizzeria_id
 where p.gender = 'female'
 except all
 select pz.name as pizzeria_name
 from person as p
 join person_visits as pv 
 	on pv.person_id = p.id
 join pizzeria as pz 
 	on pz.id = pv.pizzeria_id
 where p.gender = 'male')
union all
(select pz.name as pizzeria_name
 from person as p
 join person_visits as pv 
 	on pv.person_id = p.id
 join pizzeria as pz 
 	on pz.id = pv.pizzeria_id
 where p.gender = 'male'
 except all
 select pz.name as pizzeria_name
 from person as p
 join person_visits as pv 
 	on pv.person_id = p.id
 join pizzeria as pz 
 	on pz.id = pv.pizzeria_id
 where p.gender = 'female')
ORDER BY 1