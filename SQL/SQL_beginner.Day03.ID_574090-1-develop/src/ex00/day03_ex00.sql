select m.pizza_name, m.price, pz.name AS pizzeria_name, pv.visit_date
from menu as m
join pizzeria as pz 
	on pz.id = m.pizzeria_id
join person_visits as pv 
	on pv.pizzeria_id = pz.id
join person as p 
	on p.id = pv.person_id
where m.price between 800 and 1000 and p.name = 'Kate'
ORDER BY 1, 2, 3