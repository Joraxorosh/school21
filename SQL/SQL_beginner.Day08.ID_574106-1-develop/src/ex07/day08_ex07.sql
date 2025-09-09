-- session #1
begin transaction;
update pizzeria set rating = 2 where id = 1;
update pizzeria set rating = 4 where id = 2;
commit;

-- session #2
begin transaction;
update pizzeria set rating = 3 where id = 2;
update pizzeria set rating = 3 where id = 1;
commit;