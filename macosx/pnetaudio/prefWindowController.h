//
//  prefWindowController.h
//  pnetaudio
//
//  Created by Thomas de Grivel on 24/10/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>


@interface prefWindowController : NSWindowController {
@private
    IBOutlet NSTextField            *hostField;
    IBOutlet NSTextField            *portField;
}

@property(retain) IBOutlet NSTextField      *hostField;
@property(retain) IBOutlet NSTextField      *portField;

- (void)windowDidLoad;
- (IBAction)doPreferences:(id)sender;

@end
