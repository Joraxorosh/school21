create unique index idx_menu_unique on menu(pizzeria_id, pizza_name);

set ENABLE_SEQSCAN = off;

explain analyze
select pizzeria_id, pizza_name
from menu
where pizzeria_id = 4 and pizza_name = 'cheese pizza';