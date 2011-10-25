//
// pnetaudio - Portable Networked Audio
//
// Copyright 2011 Thomas de Grivel <billitch@gmail.com>
//
// Permission to use, copy, modify, and distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
// WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
// ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
// WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
// ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
// OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
//
// macosx/ui/ - User interface for Mac OS X
// prefWindowController - Preferences window
//

#import "prefWindowController.h"

@implementation prefWindowController

@synthesize hostField;
@synthesize portField;

- (void)windowDidLoad
{
    [hostField bind:@"value"
           toObject:[NSUserDefaultsController sharedUserDefaultsController]
        withKeyPath:@"values.host"
            options:[NSDictionary dictionaryWithObject:@"192.168.3.42"
                                                forKey:@"NSContinuouslyUpdatesValue"]];
    [portField bind:@"value"
           toObject:[NSUserDefaultsController sharedUserDefaultsController]
        withKeyPath:@"values.port"
            options:[NSDictionary dictionaryWithObject:[NSNumber numberWithInteger:9636]
                                                forKey:@"NSContinuouslyUpdatesValue"]];
}

- (IBAction)doPreferences:(id)sender
{
    [self showWindow:[self window]];
    [NSApp activateIgnoringOtherApps:YES];
}

@end
