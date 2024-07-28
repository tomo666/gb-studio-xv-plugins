# gb-studio-xv-plugins

## [日本語版はこちら (Japanese version link)](README_jaJP.md)

Experimental GB Studio 4 plugin collections

## Overview
These are byproducts of the game “XV” I’m currently developing. These plugins provide functionalities that cannot be accomplished or are difficult to implement using just the built-in event components (as of version 4.0.1).

Usability might not be straight forward and might be difficult understanding the concepts, but if it can be of any good usage depending on your needs, please feel free to use/customize it. 
Can be used in commercial or non-commercial purposes. However, these plugins are highly experimental and can be removed/updated in the future without prior notices. Also, issue fixes and additional features are not guaranteed to be implemented unless I feel the need to be updated. So please use it at your own risk.

No need for credits, but if you would like to do so, please use: Tomo@indiegdevstdio or just Tomo.

## Contents
- Array_Factory `[Virtual Array Management Plugin Collections]`
  - Array_Manager_Set `[Merges multiple global variables and use it as a virtual array (SET VALUE)]`
  - Array_Manager_Get `[Merges multiple global variables and use it as a virtual array (GET VALUE)]`
- Obstacle_Checker `[Collision Detection Plugin Collections]`
  - Actor_Walkability_Checker `[Obtains an obstacle info relative to the actor's facing direction]`
  - Obstacle_Checker `[Obtains an obstacle info at a specific tile position]`
- Sprite_Tile_Replacer `[Replaces a specified sprite tile with ability to select a VRAM bank]`

---

## Installation

Download the plugin from this repository: [Code] > [Download ZIP], and unzip the file.

![download_from_github](https://github.com/user-attachments/assets/6e3d38ac-03a1-4402-ac57-90d59e8e522b)


Under “plugins” located inside your GB Studio project folder, copy the plugins inside the "enUS" folder that you wish to use.

* Note that the plugins folder should be directly placed in your GB Studio project folder and not in the “assets” folder.

![plugin_install](https://github.com/user-attachments/assets/1f991de8-b7b3-42e1-b0b8-8fab141a18c7)

Locate the plugin under [Add Event] > [XV Plugins] and add the event.

![adding_plugin_event_enUS](https://github.com/user-attachments/assets/8f75d7ab-8bd1-4695-aca4-1c670e6519fa)
![add_events_sample_enUS](https://github.com/user-attachments/assets/70bf7898-ade7-4533-b9e6-a55d99fa3b9e)
---

## Description

***Array_Factory*** `[Virtual Array Management Plugin Collections]`

- Array_Manager_Set `[Merges multiple global variables and use it as a virtual array (SET VALUE)]`

  Merges a maximum of 16 global variables and creates a virtual 1-dimentional array. Also, individual global variables can be divided into smaller segments which allows more array elements to be used, by sacrificing the storage amount that can be used in each array element. This array division settings can be configured in the [Individual Array Element Bit Size] property. The maximum amount an array element can store according to the bit size is as follows. <1 bit> = 256, <2 bit> = 128, <4 bit> = 64, <8 bit> = 32, <16 bit> = 16.

  ![array_manager_set_event_enUS](https://github.com/user-attachments/assets/704d7fa7-7223-4483-b712-e397b47eb44f)


<dl>
<dt>Global Variables 1 - 16</dt>
<dd>
  Specify the global variables that will be merged. Merged global variables are now trated as a single “Virtual Global Variable”. A Virtual Global Variable is assigned with index numbers, so for example if you want to access global variable 3, you can acces it like an array <Virtual Global Variable[2]> (Note: Index numbers begin with 0).

  ![array_manager_virtual_array_concept_enUS](https://github.com/user-attachments/assets/2b5e4a68-461a-4a32-9499-09ae92b52863)
    
</dd>
<dt>Number of Global Variables to Use</dt>
<dd>
  From the global variables set, specify the number of global variables to be merged (counting from top). In the screenshot example above, if “2” is specified, global variables 1 and 2 will be used and others will be ignored. If the default value 16 is specified, all global variables set will be merged.
</dd>
<dt>Individual Array Element Bit Size</dt>
<dd>To use more arrays, you can divide individual global variables with the bit size you want. GB Studio’s global variable has 16 bit size each, so you can divide up the bit size in the range of 1, 2, 4, 8, 16. For example, if “2” bit is specified, each global variables will be divided into 8 segments (having 2 bit worth of storage per segment). If “8” bit is specified, each global variables will be divided into 2 segments (having 8 bit each per segment).
  
  ![Array_Manager_bit_divide_enUS](https://github.com/user-attachments/assets/833a7961-fe7f-4cbe-bef7-e83cf492a6f6)

  
  If global variable is divided in the [Individual Array Element Bit Size] property as “8” bit or “16” bit, negative values can be used for each element. The minimum and maximum values that can be used per array element is as follows. <1 bit> = 0 - 1, <2 bit> = 0 - 3, <4 bit> = 0 - 15, <8 bit> = -128 - 127, <16 bit> = -32,768 - 32,767.
</dd>
<dt>Array Index</dt>
<dd>Specify the index in the Virtual Global Variable to be manipulated on. For example, if you merged 16 global variables divided by 1 bit segment, you can address indexes between 0 and 255.</dd>
<dt>Set Value</dt>
<dd>The value (number or variable) to be stored into the specified array index.</dd>
</dl>

**Example of 16 global variables merged**

| Individual Array Element Bit Size | Array Size | Min - Max value |
|:-----------|:------------:|:------------:|
| 1 | 256 |0〜1|
| 2 | 128 |0〜3|
| 4 | 64 |0〜15|
| 8 | 32 |-128〜127|
| 16 | 16 |-32,768〜32,767|

---

- Array_Manager_Get `[Merges multiple global variables and use it as a virtual array (GET VALUE)]`

  Obtains a value from the array index of Virtual Global Variable that was set with the Array_Manager_Set plugin.
  
  ![array_manager_get_event_enUS](https://github.com/user-attachments/assets/c703a3a1-181e-4e62-9a00-367ef125576d)

<dl>
<dt>Global Variables 1 - 16</dt>
<dd>Specify the global variables that you want to merge. This should be same as the global variables set in Array_Manager_Set.</dd>
<dt>Number of Global Variables to Use</dt>
<dd>From the global variables set, specify the number of global variables to be merged (counting from top). Typically, you want to set the same value specified in Array_Manager_Set.</dd>
<dt>Individual Array Element Bit Size</dt>
<dd>Specify how many bits you like to divide each global variable with. Typically, you want to set the same value specified in Array_Manager_Set.</dd>
<dt>Array Index</dt>
<dd>Specify the index in the Virtual Global Variable to be manipulated on. For more info, refer to the description of Array_Manager_Set.</dd>
<dt>Get Value Storage Variable</dt>
<dd>The variable to store the obtained value.</dd>
</dl>

___

**(GB Studio v4.0.1) Notes when using the plugins inside custome events.**

  GBS 4.0.1 seems to have an issue of storing values into variable that are passed By Ref. When a variable is set as By Ref and tried to assign it with a value via a plugin, the value is not assigned and sets to 0. When you assign a value directly to the referenced variable using only custom event scripts, this issue does not happen. So, the current workaround is to add an extra variable assignment script inside the custom event script before assigning to the By Ref var.

  Example

  
  ![gbs401_cs_reference_issue_workaround_enUS](https://github.com/user-attachments/assets/2930e173-d973-4a23-aa93-08751af33663)

---
***Obstacle_Checker*** `[Collision Detection Plugin Collections]`

- Actor_Walkability_Checker `[Obtains an obstacle info relative to the actor's facing direction]`

  Checks for any obstacle (collisions or other actors) found relative to the specified actor's position and facing direction,  given the offset tile amount to walk relatively towards the destination. If there are no collisions or other actors, it means there are no obstacles, and 0 will be assigned to the specified return variable. Otherwise, this plugin will return the obstacle ID information. Example: No obstacle = 0, Obstacle found = Collision ID, or the actor ID represented with a negative value (Note that if the obstacle was a Player actor, the returned ID will be -128). If a map collision ID is found, the actor/player ID will be ignored. * Only 8x8 tile size is supported.

  ![actor_walkability_checker](https://github.com/user-attachments/assets/3e9047c7-851e-4afc-8534-1fdd778b5e97)

---
  
- Obstacle_Checker `[Obtains an obstacle info at the specified tile position]`

  Given the tile position (X,Y), checks if there are any obstacles (collisions or actors) on that tile. If there are no collisions or other actors on the tile, 0 will be assigned to the specified return variable. Otherwise, this plugin will return the obstacle ID information. Example: No obstacle = 0, Obstacle found = Collision ID, or the actor ID represented with a negative value (Note that if the obstacle was a Player actor, the returned ID will be -128). If a map collision ID is found, the actor/player ID will be ignored. * Only 8x8 tile size is supported.

  ![obstacle_checker](https://github.com/user-attachments/assets/acdb7f39-8023-4e32-ad93-7669a49aefff)

---

***Sprite_Tile_Replacer*** `[Replaces a specified sprite tile with ability to select a VRAM bank]`

  Replaces a sprite tile with another tileset tile. Basic functionality is same as the GBVM command: VM_ACTOR_REPLACE_TILE. However, in GB Studio up to version 4.0.1, Color Only mode does not allow you to access extended VRAM bank. This plugin will allow you to specify which VRAM bank to reference.

  ![sprite_tiles_replace_plugin_event](https://github.com/user-attachments/assets/86c5d6a6-7970-4433-b330-bafeb2b08653)

    <dl>
  <dt>Actor</dt>
  <dd>The actor in which you want to replace the sprite’s tile.</dd>
  <dt>VRAM Bank</dt>
  <dd>
    The bank you want to reference. 0 = Bank 0, 1 = Bank 1. ![vram_banks_explained](https://github.com/user-attachments/assets/b96ea501-889b-43a9-91f1-4d82c9115780)
    
  </dd>
  <dt>Tile Bank</dt>
  <dd>The source tile bank reference to use for replacing.</dd>
  <dt>Tileset</dt>
  <dd>The source tileset reference to use for replacing.</dd>
  <dt>Background Tile Index</dt>
  <dd>The background tile index in the source tileset to replace with.</dd>
  <dt>Sprite Tile Index</dt>
  <dd>The sprite’s tile index to be replaced by the background tile.</dd>
  </dl>

___
  **How do I obtain the sprite tile index?**

  Sprite tiles are scattered elsewhere in somewhat random position inside the VRAM bank(s). First you will need to check which tile index is the one to be replaced. One way of doing this is to create an event like the one below (using this plugin!) and replacing all sprite tiles with a tile image with numberings on it (placeholder tiles).
  
  ![generate_placeholder_tiles](https://github.com/user-attachments/assets/202725fb-9261-4752-8fcc-70c21e99e692)

  Then, once you run the scene, you will see the sprite being replaced with these placeholder tiles which makes it more visible which index to be used as the replacement tile. 
  Note that if the [Flip ‘Right’ To Create ‘Left’ Facing Frames] is checked in the Sprite Editor, the placeholder tiles will be flipped as well.  

  ![placeholder_tiles_applied](https://github.com/user-attachments/assets/49f250ca-a2a8-4f4b-9aa8-ddbc227a06a7)

  The placeholder tiles can be found as a sample inside this plugin for you to use if needed.
  
  ![Number_Tiles_vram0](https://github.com/user-attachments/assets/7c995253-0f39-4c28-9d1f-62b2ec3cb3ad)
![Number_Tiles_vram1](https://github.com/user-attachments/assets/8050849f-af5d-4aac-a8cd-963ece7dd773)
