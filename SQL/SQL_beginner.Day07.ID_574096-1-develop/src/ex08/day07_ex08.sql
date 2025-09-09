select p.address, pz.name, count(*) as count_of_orders
from person_order as po
join menu as m 
	on m.id = po.menu_id
join pizzeria as pz 
	on m.pizzeria_id = pz.id
join person p 
	on p.id = po.person_id
group by p.address, pz.name
order by 1, 2;