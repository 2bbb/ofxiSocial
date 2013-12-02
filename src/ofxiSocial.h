//
//  ofxiSocial.h
//
//  Created by ISHII 2bit on 2013/12/02.
//
//

#ifndef __ofxiSocial__
#define __ofxiSocial__

#import <Social/Social.h>
#include "ofMain.h"
#import "ofxiOS.h"
#import "ofxiOSExtras.h"
#import "ofxObjective-C++Utility.h"

typedef enum {
    ofxiSocialServiceTypeTwitter,
    ofxiSocialServiceTypeFacebook,
} ofxiSocialServiceType;

class ofxiSocial {
public:
    static void share(ofxiSocialServiceType type, string text, ofImage &image) {
        ofxiSocial::share(type, text, "", image);
    }
    
    static void share(ofxiSocialServiceType type, string text, string url, ofImage &image) {
        ofxiSocial::share(type, text, url, [UIImage imageWithCGImage:convert(image)]);
    }
    
    static void share(ofxiSocialServiceType type, string text, string url = "") {
        ofxiSocial::share(type, text, url, nil);
    }
private:
    static void share(ofxiSocialServiceType type, string text, string url, UIImage *image) {
        NSString *serviceType = nil;
        switch(type) {
            case ofxiSocialServiceTypeTwitter:
                serviceType = SLServiceTypeTwitter;
                break;
            case ofxiSocialServiceTypeFacebook:
                serviceType = SLServiceTypeFacebook;
                break;
            default:
                break;
        }
        if(serviceType == nil) {
            ofLogError() << "Service Type is invalid.";
            return;
        }
        SLComposeViewController *controller = [SLComposeViewController composeViewControllerForServiceType:serviceType];
        [controller setInitialText:convert(text)];
        
        if(url != "") [controller addURL:[NSURL URLWithString:convert(url)]];
        if(image) [controller addImage:image];
        [controller setCompletionHandler:^(SLComposeViewControllerResult result) {
            
        }];
        [[[[UIApplication sharedApplication] keyWindow] rootViewController] presentViewController:controller
                                                                                         animated:YES
                                                                                       completion:nil];
    }
};

#endif /* defined(__ofxiSocial__) */
