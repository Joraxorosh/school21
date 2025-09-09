select pz.name as pizzeria_name
from person_visits as pv
join person as p 
	on p.id = pv.person_id
join pizzeria as pz 
	on pz.id = pv.pizzeria_id
where p.name = 'Andrey'
except
select pz.name as pizzeria_name
from person_order as po
join person as p 
	on p.id = po.person_id
join menu as m 
	on m.id = po.menu_id
join pizzeria as pz 
	on pz.id = m.pizzeria_id
where p.name = 'Andrey'
order by 1