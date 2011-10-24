//
//  pnetaudioAppDelegate.h
//  pnetaudio
//
//  Created by Thomas de Grivel on 24/10/11.
//  Copyright 2011 Thomas de Grivel. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface pnetaudioAppDelegate : NSObject <NSApplicationDelegate> {
@private
    NSStatusItem *statusItem;
    NSMenu *menu;
}

@property (retain) IBOutlet NSStatusItem *statusItem;
@property (retain) IBOutlet NSMenu *statusMenu;

@end
