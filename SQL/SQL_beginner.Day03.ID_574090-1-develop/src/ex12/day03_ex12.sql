insert into person_order(id, person_id, menu_id, order_date)
select nid + (select max(id) from person_order) as id, 
	   p.id as person_id,
       (select id from menu where pizza_name = 'greek pizza') as menu_id,
       '2022-02-25' as order_date
from person as p
join generate_series(1, (select count(*) from person)) as nid 
	on nid = p.id