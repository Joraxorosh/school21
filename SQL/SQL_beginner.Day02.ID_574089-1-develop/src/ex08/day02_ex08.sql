select p.name
from person as p
join person_order as po
on po.person_id = p.id
join menu as m
on m.id = po.menu_id
where p.gender = 'male' 
	and p.address in ('Moscow', 'Samara')
	and m.pizza_name in ('pepperoni pizza', 'mushroom pizza')
order by 1 desc