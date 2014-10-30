//
//  CustomAlertView.h
//
//  Created by Glenn R. Bloom on 5/10/10.
//  Copyright 2010 idvance LLC. All rights reserved.
//

#import <UIKit/UIKit.h>


@interface CustomAlertView : UIAlertView {

}
+ (void) setBackgroundColor:(UIColor *) background withStrokeColor:(UIColor *) stroke;
+(void)showSimpleAlertWithTitle: (NSString *)t
                        message: (NSString *)m;

@end
