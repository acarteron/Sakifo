Sakilol
======

Visualisation rules once post processed by AlainPeters lib
Rule management with compiler capabilities

requirements
============

* compiler supporting C++14
* poco c++ lib
* AlainPeters lib
* Zamzama lib

setup
=====

to make:
 ```$ make```

to make doc:
 ```$ make doc```

to clean:
 ```$ make clean```

to full clean:
 ```$ make raz```

	
TODO
====

Fix force write rule (it always force write)

Add rule order management following order.json file structure (see sati project)

DONE
====


IMPORTANT
=========
Save rule request:
{"rule":"departure_alert","timestamp":1501530295017,"events":[{"StreamEvent":{"Role":{"kind":"Calendar","location":"Night"},"status":"28800","timestamp":"1447102800000","user":"8002"}},{"StreamEvent":{"Role":{"kind":"Door","location":"Entrance"},"status":"open","timestamp":"1447128300000","user":"8002"}}]}

RULE MANAGER
============

url/rulemanager