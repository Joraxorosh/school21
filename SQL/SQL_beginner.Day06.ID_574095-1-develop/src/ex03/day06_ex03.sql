create unique index idx_person_discounts_unique on person_discounts(person_id, pizzeria_id);

set ENABLE_SEQSCAN = off;

explain analyse
select *
from person_discounts
where person_id = 7 and pizzeria_id = 2;